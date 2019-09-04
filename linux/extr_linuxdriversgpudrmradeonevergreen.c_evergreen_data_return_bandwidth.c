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
struct evergreen_wm_params {int sclk; } ;
struct TYPE_7__ {void* full; } ;
typedef  TYPE_1__ fixed20_12 ;

/* Variables and functions */
 void* dfixed_const (int) ; 
 void* dfixed_div (TYPE_1__,TYPE_1__) ; 
 void* dfixed_mul (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  dfixed_trunc (TYPE_1__) ; 

__attribute__((used)) static u32 evergreen_data_return_bandwidth(struct evergreen_wm_params *wm)
{
	/* Calculate the display Data return Bandwidth */
	fixed20_12 return_efficiency; /* 0.8 */
	fixed20_12 sclk, bandwidth;
	fixed20_12 a;

	a.full = dfixed_const(1000);
	sclk.full = dfixed_const(wm->sclk);
	sclk.full = dfixed_div(sclk, a);
	a.full = dfixed_const(10);
	return_efficiency.full = dfixed_const(8);
	return_efficiency.full = dfixed_div(return_efficiency, a);
	a.full = dfixed_const(32);
	bandwidth.full = dfixed_mul(a, sclk);
	bandwidth.full = dfixed_mul(bandwidth, return_efficiency);

	return dfixed_trunc(bandwidth);
}