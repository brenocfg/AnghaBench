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
struct TYPE_2__ {double ReturnBW; void* LastPixelOfLineExtraWatermark; } ;
struct display_mode_lib {TYPE_1__ vba; } ;
typedef  enum output_format_class { ____Placeholder_output_format_class } output_format_class ;

/* Variables and functions */
 int dm_420 ; 
 unsigned int dml_ceil (double,int) ; 
 double dml_floor (double,int) ; 
 void* dml_max (void*,double) ; 

__attribute__((used)) static bool CalculateDelayAfterScaler(
		struct display_mode_lib *mode_lib,
		double ReturnBW,
		double ReadBandwidthPlaneLuma,
		double ReadBandwidthPlaneChroma,
		double TotalDataReadBandwidth,
		double DisplayPipeLineDeliveryTimeLuma,
		double DisplayPipeLineDeliveryTimeChroma,
		double DPPCLK,
		double DISPCLK,
		double PixelClock,
		unsigned int DSCDelay,
		unsigned int DPPPerPlane,
		bool ScalerEnabled,
		unsigned int NumberOfCursors,
		double DPPCLKDelaySubtotal,
		double DPPCLKDelaySCL,
		double DPPCLKDelaySCLLBOnly,
		double DPPCLKDelayCNVCFormater,
		double DPPCLKDelayCNVCCursor,
		double DISPCLKDelaySubtotal,
		unsigned int ScalerRecoutWidth,
		enum output_format_class OutputFormat,
		unsigned int HTotal,
		unsigned int SwathWidthSingleDPPY,
		double BytePerPixelDETY,
		double BytePerPixelDETC,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		bool Interlace,
		bool ProgressiveToInterlaceUnitInOPP,
		double *DSTXAfterScaler,
		double *DSTYAfterScaler
		)
{
	unsigned int DPPCycles, DISPCLKCycles;
	double DataFabricLineDeliveryTimeLuma;
	double DataFabricLineDeliveryTimeChroma;
	double DSTTotalPixelsAfterScaler;

	DataFabricLineDeliveryTimeLuma = SwathWidthSingleDPPY * SwathHeightY * dml_ceil(BytePerPixelDETY, 1) / (mode_lib->vba.ReturnBW * ReadBandwidthPlaneLuma / TotalDataReadBandwidth);
	mode_lib->vba.LastPixelOfLineExtraWatermark = dml_max(mode_lib->vba.LastPixelOfLineExtraWatermark, DataFabricLineDeliveryTimeLuma - DisplayPipeLineDeliveryTimeLuma);

	if (BytePerPixelDETC != 0) {
		DataFabricLineDeliveryTimeChroma = SwathWidthSingleDPPY / 2 * SwathHeightC * dml_ceil(BytePerPixelDETC, 2) / (mode_lib->vba.ReturnBW * ReadBandwidthPlaneChroma / TotalDataReadBandwidth);
		mode_lib->vba.LastPixelOfLineExtraWatermark = dml_max(mode_lib->vba.LastPixelOfLineExtraWatermark, DataFabricLineDeliveryTimeChroma - DisplayPipeLineDeliveryTimeChroma);
	}

	if (ScalerEnabled)
		DPPCycles = DPPCLKDelaySubtotal + DPPCLKDelaySCL;
	else
		DPPCycles = DPPCLKDelaySubtotal + DPPCLKDelaySCLLBOnly;

	DPPCycles = DPPCycles + DPPCLKDelayCNVCFormater + NumberOfCursors * DPPCLKDelayCNVCCursor;

	DISPCLKCycles = DISPCLKDelaySubtotal;

	if (DPPCLK == 0.0 || DISPCLK == 0.0)
		return true;

	*DSTXAfterScaler = DPPCycles * PixelClock / DPPCLK + DISPCLKCycles * PixelClock / DISPCLK
			+ DSCDelay;

	if (DPPPerPlane > 1)
		*DSTXAfterScaler = *DSTXAfterScaler + ScalerRecoutWidth;

	if (OutputFormat == dm_420 || (Interlace && ProgressiveToInterlaceUnitInOPP))
		*DSTYAfterScaler = 1;
	else
		*DSTYAfterScaler = 0;

	DSTTotalPixelsAfterScaler = ((double) (*DSTYAfterScaler * HTotal)) + *DSTXAfterScaler;
	*DSTYAfterScaler = dml_floor(DSTTotalPixelsAfterScaler / HTotal, 1);
	*DSTXAfterScaler = DSTTotalPixelsAfterScaler - ((double) (*DSTYAfterScaler * HTotal));

	return true;
}