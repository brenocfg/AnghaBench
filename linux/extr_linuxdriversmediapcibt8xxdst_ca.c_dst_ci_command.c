#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dst_state {int /*<<< orphan*/  dst_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_ERROR ; 
 int /*<<< orphan*/  DST_CA_INFO ; 
 int /*<<< orphan*/  DST_CA_NOTICE ; 
 int EIO ; 
 int GET_ACK ; 
 int /*<<< orphan*/  LONG_DELAY ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  dst_comm_init (struct dst_state*) ; 
 int /*<<< orphan*/  dst_error_recovery (struct dst_state*) ; 
 scalar_t__ dst_pio_disable (struct dst_state*) ; 
 int /*<<< orphan*/  dst_wait_dst_ready (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ read_dst (struct dst_state*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  verbose ; 
 scalar_t__ write_dst (struct dst_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dst_ci_command(struct dst_state* state, u8 * data, u8 *ca_string, u8 len, int read)
{
	u8 reply;

	mutex_lock(&state->dst_mutex);
	dst_comm_init(state);
	msleep(65);

	if (write_dst(state, data, len)) {
		dprintk(verbose, DST_CA_INFO, 1, " Write not successful, trying to recover");
		dst_error_recovery(state);
		goto error;
	}
	if ((dst_pio_disable(state)) < 0) {
		dprintk(verbose, DST_CA_ERROR, 1, " DST PIO disable failed.");
		goto error;
	}
	if (read_dst(state, &reply, GET_ACK) < 0) {
		dprintk(verbose, DST_CA_INFO, 1, " Read not successful, trying to recover");
		dst_error_recovery(state);
		goto error;
	}
	if (read) {
		if (! dst_wait_dst_ready(state, LONG_DELAY)) {
			dprintk(verbose, DST_CA_NOTICE, 1, " 8820 not ready");
			goto error;
		}
		if (read_dst(state, ca_string, 128) < 0) {	/*	Try to make this dynamic	*/
			dprintk(verbose, DST_CA_INFO, 1, " Read not successful, trying to recover");
			dst_error_recovery(state);
			goto error;
		}
	}
	mutex_unlock(&state->dst_mutex);
	return 0;

error:
	mutex_unlock(&state->dst_mutex);
	return -EIO;
}