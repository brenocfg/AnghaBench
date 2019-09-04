#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct dce6_wm_params {int disp_clk; } ;
struct TYPE_7__ {void* full; } ;
typedef  TYPE_1__ fixed20_12 ;

/* Variables and functions */
 void* dfixed_const (int) ; 
 void* dfixed_div (TYPE_1__,TYPE_1__) ; 
 void* dfixed_mul (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  dfixed_trunc (TYPE_1__) ; 

__attribute__((used)) static u32 dce_v6_0_dmif_request_bandwidth(struct dce6_wm_params *wm)
{
	/* Calculate the DMIF Request Bandwidth */
	fixed20_12 disp_clk_request_efficiency; /* 0.8 */
	fixed20_12 disp_clk, bandwidth;
	fixed20_12 a, b;

	a.full = dfixed_const(1000);
	disp_clk.full = dfixed_const(wm->disp_clk);
	disp_clk.full = dfixed_div(disp_clk, a);
	a.full = dfixed_const(32);
	b.full = dfixed_mul(a, disp_clk);

	a.full = dfixed_const(10);
	disp_clk_request_efficiency.full = dfixed_const(8);
	disp_clk_request_efficiency.full = dfixed_div(disp_clk_request_efficiency, a);

	bandwidth.full = dfixed_mul(b, disp_clk_request_efficiency);

	return dfixed_trunc(bandwidth);
}