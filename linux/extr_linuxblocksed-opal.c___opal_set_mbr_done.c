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
typedef  int u8 ;
struct opal_step {int* member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int opal_key ;
struct opal_dev {struct opal_step const* steps; } ;

/* Variables and functions */
 int /*<<< orphan*/ * end_opal_session ; 
 int next (struct opal_dev*) ; 
 int /*<<< orphan*/ * opal_discovery0 ; 
 int /*<<< orphan*/ * set_mbr_done ; 
 int /*<<< orphan*/ * start_admin1LSP_opal_session ; 

__attribute__((used)) static int __opal_set_mbr_done(struct opal_dev *dev, struct opal_key *key)
{
	u8 mbr_done_tf = 1;
	const struct opal_step mbrdone_step [] = {
		{ opal_discovery0, },
		{ start_admin1LSP_opal_session, key },
		{ set_mbr_done, &mbr_done_tf },
		{ end_opal_session, },
		{ NULL, }
	};

	dev->steps = mbrdone_step;
	return next(dev);
}