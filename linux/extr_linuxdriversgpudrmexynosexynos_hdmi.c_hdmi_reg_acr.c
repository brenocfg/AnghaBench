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
struct hdmi_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_ACR_CON ; 
 int /*<<< orphan*/  HDMI_ACR_CTS0 ; 
 int /*<<< orphan*/  HDMI_ACR_MCTS0 ; 
 int /*<<< orphan*/  HDMI_ACR_N0 ; 
 int /*<<< orphan*/  hdmi_reg_writeb (struct hdmi_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_reg_writev (struct hdmi_context*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hdmi_reg_acr(struct hdmi_context *hdata, u32 freq)
{
	u32 n, cts;

	cts = (freq % 9) ? 27000 : 30000;
	n = 128 * freq / (27000000 / cts);

	hdmi_reg_writev(hdata, HDMI_ACR_N0, 3, n);
	hdmi_reg_writev(hdata, HDMI_ACR_MCTS0, 3, cts);
	hdmi_reg_writev(hdata, HDMI_ACR_CTS0, 3, cts);
	hdmi_reg_writeb(hdata, HDMI_ACR_CON, 4);
}