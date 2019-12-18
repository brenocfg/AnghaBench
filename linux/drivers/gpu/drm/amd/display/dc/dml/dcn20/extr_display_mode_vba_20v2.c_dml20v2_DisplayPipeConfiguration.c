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
struct TYPE_2__ {unsigned int NumberOfActivePlanes; scalar_t__* SourcePixelFormat; scalar_t__* SurfaceTiling; scalar_t__* SourceScan; double* ViewportWidth; double* ViewportHeight; int* ODMCombineEnabled; unsigned int* BlendingAndTiming; double* HActive; double* HRatio; double* DPPPerPlane; double DETBufferSizeInKByte; double* SwathHeightY; double* SwathHeightC; int* DETBufferSizeY; double* DETBufferSizeC; } ;
struct display_mode_lib {TYPE_1__ vba; } ;

/* Variables and functions */
 scalar_t__ dm_420_10 ; 
 scalar_t__ dm_420_8 ; 
 scalar_t__ dm_444_16 ; 
 scalar_t__ dm_444_32 ; 
 scalar_t__ dm_444_64 ; 
 scalar_t__ dm_444_8 ; 
 scalar_t__ dm_horz ; 
 scalar_t__ dm_sw_4kb_s ; 
 scalar_t__ dm_sw_4kb_s_x ; 
 scalar_t__ dm_sw_64kb_s ; 
 scalar_t__ dm_sw_64kb_s_t ; 
 scalar_t__ dm_sw_64kb_s_x ; 
 scalar_t__ dm_sw_linear ; 
 scalar_t__ dm_sw_var_s ; 
 scalar_t__ dm_sw_var_s_x ; 
 int dml_ceil (double,int) ; 
 double dml_min (double,double) ; 

__attribute__((used)) static void dml20v2_DisplayPipeConfiguration(struct display_mode_lib *mode_lib)
{
	double BytePerPixDETY;
	double BytePerPixDETC;
	double Read256BytesBlockHeightY;
	double Read256BytesBlockHeightC;
	double Read256BytesBlockWidthY;
	double Read256BytesBlockWidthC;
	double MaximumSwathHeightY;
	double MaximumSwathHeightC;
	double MinimumSwathHeightY;
	double MinimumSwathHeightC;
	double SwathWidth;
	double SwathWidthGranularityY;
	double SwathWidthGranularityC;
	double RoundedUpMaxSwathSizeBytesY;
	double RoundedUpMaxSwathSizeBytesC;
	unsigned int j, k;

	for (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) {
		bool MainPlaneDoesODMCombine = false;

		if (mode_lib->vba.SourcePixelFormat[k] == dm_444_64) {
			BytePerPixDETY = 8;
			BytePerPixDETC = 0;
		} else if (mode_lib->vba.SourcePixelFormat[k] == dm_444_32) {
			BytePerPixDETY = 4;
			BytePerPixDETC = 0;
		} else if (mode_lib->vba.SourcePixelFormat[k] == dm_444_16) {
			BytePerPixDETY = 2;
			BytePerPixDETC = 0;
		} else if (mode_lib->vba.SourcePixelFormat[k] == dm_444_8) {
			BytePerPixDETY = 1;
			BytePerPixDETC = 0;
		} else if (mode_lib->vba.SourcePixelFormat[k] == dm_420_8) {
			BytePerPixDETY = 1;
			BytePerPixDETC = 2;
		} else {
			BytePerPixDETY = 4.0 / 3.0;
			BytePerPixDETC = 8.0 / 3.0;
		}

		if ((mode_lib->vba.SourcePixelFormat[k] == dm_444_64
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_32
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_16
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_8)) {
			if (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) {
				Read256BytesBlockHeightY = 1;
			} else if (mode_lib->vba.SourcePixelFormat[k] == dm_444_64) {
				Read256BytesBlockHeightY = 4;
			} else if (mode_lib->vba.SourcePixelFormat[k] == dm_444_32
					|| mode_lib->vba.SourcePixelFormat[k] == dm_444_16) {
				Read256BytesBlockHeightY = 8;
			} else {
				Read256BytesBlockHeightY = 16;
			}
			Read256BytesBlockWidthY = 256 / dml_ceil(BytePerPixDETY, 1)
					/ Read256BytesBlockHeightY;
			Read256BytesBlockHeightC = 0;
			Read256BytesBlockWidthC = 0;
		} else {
			if (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) {
				Read256BytesBlockHeightY = 1;
				Read256BytesBlockHeightC = 1;
			} else if (mode_lib->vba.SourcePixelFormat[k] == dm_420_8) {
				Read256BytesBlockHeightY = 16;
				Read256BytesBlockHeightC = 8;
			} else {
				Read256BytesBlockHeightY = 8;
				Read256BytesBlockHeightC = 8;
			}
			Read256BytesBlockWidthY = 256 / dml_ceil(BytePerPixDETY, 1)
					/ Read256BytesBlockHeightY;
			Read256BytesBlockWidthC = 256 / dml_ceil(BytePerPixDETC, 2)
					/ Read256BytesBlockHeightC;
		}

		if (mode_lib->vba.SourceScan[k] == dm_horz) {
			MaximumSwathHeightY = Read256BytesBlockHeightY;
			MaximumSwathHeightC = Read256BytesBlockHeightC;
		} else {
			MaximumSwathHeightY = Read256BytesBlockWidthY;
			MaximumSwathHeightC = Read256BytesBlockWidthC;
		}

		if ((mode_lib->vba.SourcePixelFormat[k] == dm_444_64
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_32
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_16
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_8)) {
			if (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear
					|| (mode_lib->vba.SourcePixelFormat[k] == dm_444_64
							&& (mode_lib->vba.SurfaceTiling[k]
									== dm_sw_4kb_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_4kb_s_x
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s_t
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s_x
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_var_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_var_s_x)
							&& mode_lib->vba.SourceScan[k] == dm_horz)) {
				MinimumSwathHeightY = MaximumSwathHeightY;
			} else if (mode_lib->vba.SourcePixelFormat[k] == dm_444_8
					&& mode_lib->vba.SourceScan[k] != dm_horz) {
				MinimumSwathHeightY = MaximumSwathHeightY;
			} else {
				MinimumSwathHeightY = MaximumSwathHeightY / 2.0;
			}
			MinimumSwathHeightC = MaximumSwathHeightC;
		} else {
			if (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) {
				MinimumSwathHeightY = MaximumSwathHeightY;
				MinimumSwathHeightC = MaximumSwathHeightC;
			} else if (mode_lib->vba.SourcePixelFormat[k] == dm_420_8
					&& mode_lib->vba.SourceScan[k] == dm_horz) {
				MinimumSwathHeightY = MaximumSwathHeightY / 2.0;
				MinimumSwathHeightC = MaximumSwathHeightC;
			} else if (mode_lib->vba.SourcePixelFormat[k] == dm_420_10
					&& mode_lib->vba.SourceScan[k] == dm_horz) {
				MinimumSwathHeightC = MaximumSwathHeightC / 2.0;
				MinimumSwathHeightY = MaximumSwathHeightY;
			} else {
				MinimumSwathHeightY = MaximumSwathHeightY;
				MinimumSwathHeightC = MaximumSwathHeightC;
			}
		}

		if (mode_lib->vba.SourceScan[k] == dm_horz) {
			SwathWidth = mode_lib->vba.ViewportWidth[k];
		} else {
			SwathWidth = mode_lib->vba.ViewportHeight[k];
		}

		if (mode_lib->vba.ODMCombineEnabled[k] == true) {
			MainPlaneDoesODMCombine = true;
		}
		for (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) {
			if (mode_lib->vba.BlendingAndTiming[k] == j
					&& mode_lib->vba.ODMCombineEnabled[j] == true) {
				MainPlaneDoesODMCombine = true;
			}
		}

		if (MainPlaneDoesODMCombine == true) {
			SwathWidth = dml_min(
					SwathWidth,
					mode_lib->vba.HActive[k] / 2.0 * mode_lib->vba.HRatio[k]);
		} else {
			if (mode_lib->vba.DPPPerPlane[k] == 0)
				SwathWidth = 0;
			else
				SwathWidth = SwathWidth / mode_lib->vba.DPPPerPlane[k];
		}

		SwathWidthGranularityY = 256 / dml_ceil(BytePerPixDETY, 1) / MaximumSwathHeightY;
		RoundedUpMaxSwathSizeBytesY = (dml_ceil(
				(double) (SwathWidth - 1),
				SwathWidthGranularityY) + SwathWidthGranularityY) * BytePerPixDETY
				* MaximumSwathHeightY;
		if (mode_lib->vba.SourcePixelFormat[k] == dm_420_10) {
			RoundedUpMaxSwathSizeBytesY = dml_ceil(RoundedUpMaxSwathSizeBytesY, 256)
					+ 256;
		}
		if (MaximumSwathHeightC > 0) {
			SwathWidthGranularityC = 256.0 / dml_ceil(BytePerPixDETC, 2)
					/ MaximumSwathHeightC;
			RoundedUpMaxSwathSizeBytesC = (dml_ceil(
					(double) (SwathWidth / 2.0 - 1),
					SwathWidthGranularityC) + SwathWidthGranularityC)
					* BytePerPixDETC * MaximumSwathHeightC;
			if (mode_lib->vba.SourcePixelFormat[k] == dm_420_10) {
				RoundedUpMaxSwathSizeBytesC = dml_ceil(
						RoundedUpMaxSwathSizeBytesC,
						256) + 256;
			}
		} else
			RoundedUpMaxSwathSizeBytesC = 0.0;

		if (RoundedUpMaxSwathSizeBytesY + RoundedUpMaxSwathSizeBytesC
				<= mode_lib->vba.DETBufferSizeInKByte * 1024.0 / 2.0) {
			mode_lib->vba.SwathHeightY[k] = MaximumSwathHeightY;
			mode_lib->vba.SwathHeightC[k] = MaximumSwathHeightC;
		} else {
			mode_lib->vba.SwathHeightY[k] = MinimumSwathHeightY;
			mode_lib->vba.SwathHeightC[k] = MinimumSwathHeightC;
		}

		if (mode_lib->vba.SwathHeightC[k] == 0) {
			mode_lib->vba.DETBufferSizeY[k] = mode_lib->vba.DETBufferSizeInKByte * 1024;
			mode_lib->vba.DETBufferSizeC[k] = 0;
		} else if (mode_lib->vba.SwathHeightY[k] <= mode_lib->vba.SwathHeightC[k]) {
			mode_lib->vba.DETBufferSizeY[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 / 2;
			mode_lib->vba.DETBufferSizeC[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 / 2;
		} else {
			mode_lib->vba.DETBufferSizeY[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 * 2 / 3;
			mode_lib->vba.DETBufferSizeC[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 / 3;
		}
	}
}