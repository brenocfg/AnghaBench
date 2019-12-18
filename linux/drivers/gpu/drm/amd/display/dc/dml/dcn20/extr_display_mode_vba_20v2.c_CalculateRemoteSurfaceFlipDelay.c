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
struct display_mode_lib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*,double) ; 

__attribute__((used)) static double CalculateRemoteSurfaceFlipDelay(
		struct display_mode_lib *mode_lib,
		double VRatio,
		double SwathWidth,
		double Bpp,
		double LineTime,
		double XFCTSlvVupdateOffset,
		double XFCTSlvVupdateWidth,
		double XFCTSlvVreadyOffset,
		double XFCXBUFLatencyTolerance,
		double XFCFillBWOverhead,
		double XFCSlvChunkSize,
		double XFCBusTransportTime,
		double TCalc,
		double TWait,
		double *SrcActiveDrainRate,
		double *TInitXFill,
		double *TslvChk)
{
	double TSlvSetup, AvgfillRate, result;

	*SrcActiveDrainRate = VRatio * SwathWidth * Bpp / LineTime;
	TSlvSetup = XFCTSlvVupdateOffset + XFCTSlvVupdateWidth + XFCTSlvVreadyOffset;
	*TInitXFill = XFCXBUFLatencyTolerance / (1 + XFCFillBWOverhead / 100);
	AvgfillRate = *SrcActiveDrainRate * (1 + XFCFillBWOverhead / 100);
	*TslvChk = XFCSlvChunkSize / AvgfillRate;
	dml_print(
			"DML::CalculateRemoteSurfaceFlipDelay: SrcActiveDrainRate: %f\n",
			*SrcActiveDrainRate);
	dml_print("DML::CalculateRemoteSurfaceFlipDelay: TSlvSetup: %f\n", TSlvSetup);
	dml_print("DML::CalculateRemoteSurfaceFlipDelay: TInitXFill: %f\n", *TInitXFill);
	dml_print("DML::CalculateRemoteSurfaceFlipDelay: AvgfillRate: %f\n", AvgfillRate);
	dml_print("DML::CalculateRemoteSurfaceFlipDelay: TslvChk: %f\n", *TslvChk);
	result = 2 * XFCBusTransportTime + TSlvSetup + TCalc + TWait + *TslvChk + *TInitXFill; // TODO: This doesn't seem to match programming guide
	dml_print("DML::CalculateRemoteSurfaceFlipDelay: RemoteSurfaceFlipDelay: %f\n", result);
	return result;
}