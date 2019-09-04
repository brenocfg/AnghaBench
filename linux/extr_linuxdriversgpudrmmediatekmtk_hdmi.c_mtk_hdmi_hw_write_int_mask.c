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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRL_INT_MASK ; 
 int /*<<< orphan*/  mtk_hdmi_write (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_write_int_mask(struct mtk_hdmi *hdmi, u32 int_mask)
{
	mtk_hdmi_write(hdmi, GRL_INT_MASK, int_mask);
}