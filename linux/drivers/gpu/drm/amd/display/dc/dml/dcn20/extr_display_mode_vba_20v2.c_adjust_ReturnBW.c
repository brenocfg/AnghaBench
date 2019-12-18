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
struct TYPE_2__ {double DCFCLK; double ReturnBusWidth; int UrgentLatencyPixelDataOnly; int ROBBufferSizeInKByte; int PixelChunkSizeInKByte; } ;
struct display_mode_lib {TYPE_1__ vba; } ;

/* Variables and functions */
 double dml_min (double,double) ; 
 double dml_pow (double,int) ; 

__attribute__((used)) static double adjust_ReturnBW(
		struct display_mode_lib *mode_lib,
		double ReturnBW,
		bool DCCEnabledAnyPlane,
		double ReturnBandwidthToDCN)
{
	double CriticalCompression;

	if (DCCEnabledAnyPlane
			&& ReturnBandwidthToDCN
					> mode_lib->vba.DCFCLK * mode_lib->vba.ReturnBusWidth / 4.0)
		ReturnBW =
				dml_min(
						ReturnBW,
						ReturnBandwidthToDCN * 4
								* (1.0
										- mode_lib->vba.UrgentLatencyPixelDataOnly
												/ ((mode_lib->vba.ROBBufferSizeInKByte
														- mode_lib->vba.PixelChunkSizeInKByte)
														* 1024
														/ ReturnBandwidthToDCN
														- mode_lib->vba.DCFCLK
																* mode_lib->vba.ReturnBusWidth
																/ 4)
										+ mode_lib->vba.UrgentLatencyPixelDataOnly));

	CriticalCompression = 2.0 * mode_lib->vba.ReturnBusWidth * mode_lib->vba.DCFCLK
			* mode_lib->vba.UrgentLatencyPixelDataOnly
			/ (ReturnBandwidthToDCN * mode_lib->vba.UrgentLatencyPixelDataOnly
					+ (mode_lib->vba.ROBBufferSizeInKByte
							- mode_lib->vba.PixelChunkSizeInKByte)
							* 1024);

	if (DCCEnabledAnyPlane && CriticalCompression > 1.0 && CriticalCompression < 4.0)
		ReturnBW =
				dml_min(
						ReturnBW,
						4.0 * ReturnBandwidthToDCN
								* (mode_lib->vba.ROBBufferSizeInKByte
										- mode_lib->vba.PixelChunkSizeInKByte)
								* 1024
								* mode_lib->vba.ReturnBusWidth
								* mode_lib->vba.DCFCLK
								* mode_lib->vba.UrgentLatencyPixelDataOnly
								/ dml_pow(
										(ReturnBandwidthToDCN
												* mode_lib->vba.UrgentLatencyPixelDataOnly
												+ (mode_lib->vba.ROBBufferSizeInKByte
														- mode_lib->vba.PixelChunkSizeInKByte)
														* 1024),
										2));

	return ReturnBW;
}