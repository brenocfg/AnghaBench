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
struct TYPE_2__ {int GPUVMMaxPageTableLevels; } ;
struct display_mode_lib {TYPE_1__ vba; } ;
typedef  enum source_format_class { ____Placeholder_source_format_class } source_format_class ;
typedef  enum scan_direction_class { ____Placeholder_scan_direction_class } scan_direction_class ;

/* Variables and functions */
 int dm_420_10 ; 
 int dm_420_8 ; 
 int dm_horz ; 
 unsigned int dm_sw_4kb_d ; 
 unsigned int dm_sw_4kb_d_x ; 
 unsigned int dm_sw_4kb_s ; 
 unsigned int dm_sw_4kb_s_x ; 
 unsigned int dm_sw_64kb_d ; 
 unsigned int dm_sw_64kb_d_t ; 
 unsigned int dm_sw_64kb_d_x ; 
 unsigned int dm_sw_64kb_r_x ; 
 unsigned int dm_sw_64kb_s ; 
 unsigned int dm_sw_64kb_s_t ; 
 unsigned int dm_sw_64kb_s_x ; 
 unsigned int dm_sw_gfx7_2d_thin_gl ; 
 unsigned int dm_sw_gfx7_2d_thin_lvp ; 
 unsigned int dm_sw_linear ; 
 int dml_ceil (double,int) ; 
 scalar_t__ dml_floor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dml_log2 (unsigned int) ; 
 unsigned int dml_min (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int CalculateVMAndRowBytes(
		struct display_mode_lib *mode_lib,
		bool DCCEnable,
		unsigned int BlockHeight256Bytes,
		unsigned int BlockWidth256Bytes,
		enum source_format_class SourcePixelFormat,
		unsigned int SurfaceTiling,
		unsigned int BytePerPixel,
		enum scan_direction_class ScanDirection,
		unsigned int ViewportWidth,
		unsigned int ViewportHeight,
		unsigned int SwathWidth,
		bool GPUVMEnable,
		unsigned int VMMPageSize,
		unsigned int PTEBufferSizeInRequestsLuma,
		unsigned int PDEProcessingBufIn64KBReqs,
		unsigned int Pitch,
		unsigned int DCCMetaPitch,
		unsigned int *MacroTileWidth,
		unsigned int *MetaRowByte,
		unsigned int *PixelPTEBytesPerRow,
		bool *PTEBufferSizeNotExceeded,
		unsigned int *dpte_row_height,
		unsigned int *meta_row_height)
{
	unsigned int MetaRequestHeight;
	unsigned int MetaRequestWidth;
	unsigned int MetaSurfWidth;
	unsigned int MetaSurfHeight;
	unsigned int MPDEBytesFrame;
	unsigned int MetaPTEBytesFrame;
	unsigned int DCCMetaSurfaceBytes;

	unsigned int MacroTileSizeBytes;
	unsigned int MacroTileHeight;
	unsigned int DPDE0BytesFrame;
	unsigned int ExtraDPDEBytesFrame;
	unsigned int PDEAndMetaPTEBytesFrame;

	if (DCCEnable == true) {
		MetaRequestHeight = 8 * BlockHeight256Bytes;
		MetaRequestWidth = 8 * BlockWidth256Bytes;
		if (ScanDirection == dm_horz) {
			*meta_row_height = MetaRequestHeight;
			MetaSurfWidth = dml_ceil((double) SwathWidth - 1, MetaRequestWidth)
					+ MetaRequestWidth;
			*MetaRowByte = MetaSurfWidth * MetaRequestHeight * BytePerPixel / 256.0;
		} else {
			*meta_row_height = MetaRequestWidth;
			MetaSurfHeight = dml_ceil((double) SwathWidth - 1, MetaRequestHeight)
					+ MetaRequestHeight;
			*MetaRowByte = MetaSurfHeight * MetaRequestWidth * BytePerPixel / 256.0;
		}
		if (ScanDirection == dm_horz) {
			DCCMetaSurfaceBytes = DCCMetaPitch
					* (dml_ceil(ViewportHeight - 1, 64 * BlockHeight256Bytes)
							+ 64 * BlockHeight256Bytes) * BytePerPixel
					/ 256;
		} else {
			DCCMetaSurfaceBytes = DCCMetaPitch
					* (dml_ceil(
							(double) ViewportHeight - 1,
							64 * BlockHeight256Bytes)
							+ 64 * BlockHeight256Bytes) * BytePerPixel
					/ 256;
		}
		if (GPUVMEnable == true) {
			MetaPTEBytesFrame = (dml_ceil(
					(double) (DCCMetaSurfaceBytes - VMMPageSize)
							/ (8 * VMMPageSize),
					1) + 1) * 64;
			MPDEBytesFrame = 128 * (mode_lib->vba.GPUVMMaxPageTableLevels - 1);
		} else {
			MetaPTEBytesFrame = 0;
			MPDEBytesFrame = 0;
		}
	} else {
		MetaPTEBytesFrame = 0;
		MPDEBytesFrame = 0;
		*MetaRowByte = 0;
	}

	if (SurfaceTiling == dm_sw_linear || SurfaceTiling == dm_sw_gfx7_2d_thin_gl || SurfaceTiling == dm_sw_gfx7_2d_thin_lvp) {
		MacroTileSizeBytes = 256;
		MacroTileHeight = BlockHeight256Bytes;
	} else if (SurfaceTiling == dm_sw_4kb_s || SurfaceTiling == dm_sw_4kb_s_x
			|| SurfaceTiling == dm_sw_4kb_d || SurfaceTiling == dm_sw_4kb_d_x) {
		MacroTileSizeBytes = 4096;
		MacroTileHeight = 4 * BlockHeight256Bytes;
	} else if (SurfaceTiling == dm_sw_64kb_s || SurfaceTiling == dm_sw_64kb_s_t
			|| SurfaceTiling == dm_sw_64kb_s_x || SurfaceTiling == dm_sw_64kb_d
			|| SurfaceTiling == dm_sw_64kb_d_t || SurfaceTiling == dm_sw_64kb_d_x
			|| SurfaceTiling == dm_sw_64kb_r_x) {
		MacroTileSizeBytes = 65536;
		MacroTileHeight = 16 * BlockHeight256Bytes;
	} else {
		MacroTileSizeBytes = 262144;
		MacroTileHeight = 32 * BlockHeight256Bytes;
	}
	*MacroTileWidth = MacroTileSizeBytes / BytePerPixel / MacroTileHeight;

	if (GPUVMEnable == true && mode_lib->vba.GPUVMMaxPageTableLevels > 1) {
		if (ScanDirection == dm_horz) {
			DPDE0BytesFrame =
					64
							* (dml_ceil(
									((Pitch
											* (dml_ceil(
													ViewportHeight
															- 1,
													MacroTileHeight)
													+ MacroTileHeight)
											* BytePerPixel)
											- MacroTileSizeBytes)
											/ (8
													* 2097152),
									1) + 1);
		} else {
			DPDE0BytesFrame =
					64
							* (dml_ceil(
									((Pitch
											* (dml_ceil(
													(double) SwathWidth
															- 1,
													MacroTileHeight)
													+ MacroTileHeight)
											* BytePerPixel)
											- MacroTileSizeBytes)
											/ (8
													* 2097152),
									1) + 1);
		}
		ExtraDPDEBytesFrame = 128 * (mode_lib->vba.GPUVMMaxPageTableLevels - 2);
	} else {
		DPDE0BytesFrame = 0;
		ExtraDPDEBytesFrame = 0;
	}

	PDEAndMetaPTEBytesFrame = MetaPTEBytesFrame + MPDEBytesFrame + DPDE0BytesFrame
			+ ExtraDPDEBytesFrame;

	if (GPUVMEnable == true) {
		unsigned int PTERequestSize;
		unsigned int PixelPTEReqHeight;
		unsigned int PixelPTEReqWidth;
		double FractionOfPTEReturnDrop;
		unsigned int EffectivePDEProcessingBufIn64KBReqs;

		if (SurfaceTiling == dm_sw_linear) {
			PixelPTEReqHeight = 1;
			PixelPTEReqWidth = 8.0 * VMMPageSize / BytePerPixel;
			PTERequestSize = 64;
			FractionOfPTEReturnDrop = 0;
		} else if (MacroTileSizeBytes == 4096) {
			PixelPTEReqHeight = MacroTileHeight;
			PixelPTEReqWidth = 8 * *MacroTileWidth;
			PTERequestSize = 64;
			if (ScanDirection == dm_horz)
				FractionOfPTEReturnDrop = 0;
			else
				FractionOfPTEReturnDrop = 7 / 8;
		} else if (VMMPageSize == 4096 && MacroTileSizeBytes > 4096) {
			PixelPTEReqHeight = 16 * BlockHeight256Bytes;
			PixelPTEReqWidth = 16 * BlockWidth256Bytes;
			PTERequestSize = 128;
			FractionOfPTEReturnDrop = 0;
		} else {
			PixelPTEReqHeight = MacroTileHeight;
			PixelPTEReqWidth = 8 * *MacroTileWidth;
			PTERequestSize = 64;
			FractionOfPTEReturnDrop = 0;
		}

		if (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10)
			EffectivePDEProcessingBufIn64KBReqs = PDEProcessingBufIn64KBReqs / 2;
		else
			EffectivePDEProcessingBufIn64KBReqs = PDEProcessingBufIn64KBReqs;

		if (SurfaceTiling == dm_sw_linear) {
			*dpte_row_height =
					dml_min(
							128,
							1
									<< (unsigned int) dml_floor(
											dml_log2(
													dml_min(
															(double) PTEBufferSizeInRequestsLuma
																	* PixelPTEReqWidth,
															EffectivePDEProcessingBufIn64KBReqs
																	* 65536.0
																	/ BytePerPixel)
															/ Pitch),
											1));
			*PixelPTEBytesPerRow = PTERequestSize
					* (dml_ceil(
							(double) (Pitch * *dpte_row_height - 1)
									/ PixelPTEReqWidth,
							1) + 1);
		} else if (ScanDirection == dm_horz) {
			*dpte_row_height = PixelPTEReqHeight;
			*PixelPTEBytesPerRow = PTERequestSize
					* (dml_ceil(((double) SwathWidth - 1) / PixelPTEReqWidth, 1)
							+ 1);
		} else {
			*dpte_row_height = dml_min(PixelPTEReqWidth, *MacroTileWidth);
			*PixelPTEBytesPerRow = PTERequestSize
					* (dml_ceil(
							((double) SwathWidth - 1)
									/ PixelPTEReqHeight,
							1) + 1);
		}
		if (*PixelPTEBytesPerRow * (1 - FractionOfPTEReturnDrop)
				<= 64 * PTEBufferSizeInRequestsLuma) {
			*PTEBufferSizeNotExceeded = true;
		} else {
			*PTEBufferSizeNotExceeded = false;
		}
	} else {
		*PixelPTEBytesPerRow = 0;
		*PTEBufferSizeNotExceeded = true;
	}

	return PDEAndMetaPTEBytesFrame;
}