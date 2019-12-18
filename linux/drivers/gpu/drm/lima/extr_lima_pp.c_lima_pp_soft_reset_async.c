#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int async_reset; } ;
struct lima_ip {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_PP_CTRL ; 
 int /*<<< orphan*/  LIMA_PP_CTRL_SOFT_RESET ; 
 int /*<<< orphan*/  LIMA_PP_INT_MASK ; 
 int /*<<< orphan*/  LIMA_PP_INT_RAWSTAT ; 
 int /*<<< orphan*/  LIMA_PP_IRQ_MASK_ALL ; 
 int /*<<< orphan*/  pp_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lima_pp_soft_reset_async(struct lima_ip *ip)
{
	if (ip->data.async_reset)
		return;

	pp_write(LIMA_PP_INT_MASK, 0);
	pp_write(LIMA_PP_INT_RAWSTAT, LIMA_PP_IRQ_MASK_ALL);
	pp_write(LIMA_PP_CTRL, LIMA_PP_CTRL_SOFT_RESET);
	ip->data.async_reset = true;
}