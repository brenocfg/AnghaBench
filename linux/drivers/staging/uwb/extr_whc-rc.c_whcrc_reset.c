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
struct whcrc {int /*<<< orphan*/  umc_dev; } ;
struct uwb_rc {struct whcrc* priv; } ;

/* Variables and functions */
 int umc_controller_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int whcrc_reset(struct uwb_rc *rc)
{
	struct whcrc *whcrc = rc->priv;

	return umc_controller_reset(whcrc->umc_dev);
}