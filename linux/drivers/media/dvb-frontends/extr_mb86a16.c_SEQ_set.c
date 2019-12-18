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
struct mb86a16_state {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ mb86a16_write (struct mb86a16_state*,int,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int SEQ_set(struct mb86a16_state *state, unsigned char loop)
{
	/* SLOCK0 = 0 */
	if (mb86a16_write(state, 0x32, 0x02 | (loop << 2)) < 0) {
		dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		return -EREMOTEIO;
	}

	return 0;
}