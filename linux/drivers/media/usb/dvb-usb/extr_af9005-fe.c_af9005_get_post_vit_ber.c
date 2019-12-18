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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int af9005_get_post_vit_err_cw_count (struct dvb_frontend*,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int af9005_get_post_vit_ber(struct dvb_frontend *fe,
				   u32 * post_err_count, u32 * post_cw_count,
				   u16 * abort_count)
{
	u32 loc_cw_count = 0, loc_err_count;
	u16 loc_abort_count = 0;
	int ret;

	ret =
	    af9005_get_post_vit_err_cw_count(fe, &loc_err_count, &loc_cw_count,
					     &loc_abort_count);
	if (ret)
		return ret;
	*post_err_count = loc_err_count;
	*post_cw_count = loc_cw_count * 204 * 8;
	*abort_count = loc_abort_count;

	return 0;
}