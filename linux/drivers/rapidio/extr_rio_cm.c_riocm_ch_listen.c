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
typedef  int /*<<< orphan*/  u16 ;
struct rio_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHOP ; 
 int EINVAL ; 
 int /*<<< orphan*/  RIO_CM_CHAN_BOUND ; 
 int /*<<< orphan*/  RIO_CM_LISTEN ; 
 int /*<<< orphan*/  riocm_cmp_exch (struct rio_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct rio_channel* riocm_get_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_put_channel (struct rio_channel*) ; 

__attribute__((used)) static int riocm_ch_listen(u16 ch_id)
{
	struct rio_channel *ch = NULL;
	int ret = 0;

	riocm_debug(CHOP, "(ch_%d)", ch_id);

	ch = riocm_get_channel(ch_id);
	if (!ch)
		return -EINVAL;
	if (!riocm_cmp_exch(ch, RIO_CM_CHAN_BOUND, RIO_CM_LISTEN))
		ret = -EINVAL;
	riocm_put_channel(ch);
	return ret;
}