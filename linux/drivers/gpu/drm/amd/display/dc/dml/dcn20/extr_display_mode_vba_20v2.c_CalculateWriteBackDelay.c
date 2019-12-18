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
typedef  enum source_format_class { ____Placeholder_source_format_class } source_format_class ;

/* Variables and functions */
 int dm_444_32 ; 
 int dml_ceil (unsigned int,int) ; 
 unsigned int dml_max (double,unsigned int) ; 

__attribute__((used)) static double CalculateWriteBackDelay(
		enum source_format_class WritebackPixelFormat,
		double WritebackHRatio,
		double WritebackVRatio,
		unsigned int WritebackLumaHTaps,
		unsigned int WritebackLumaVTaps,
		unsigned int WritebackChromaHTaps,
		unsigned int WritebackChromaVTaps,
		unsigned int WritebackDestinationWidth)
{
	double CalculateWriteBackDelay =
			dml_max(
					dml_ceil(WritebackLumaHTaps / 4.0, 1) / WritebackHRatio,
					WritebackLumaVTaps * dml_ceil(1.0 / WritebackVRatio, 1)
							* dml_ceil(
									WritebackDestinationWidth
											/ 4.0,
									1)
							+ dml_ceil(1.0 / WritebackVRatio, 1)
									* (dml_ceil(
											WritebackLumaVTaps
													/ 4.0,
											1) + 4));

	if (WritebackPixelFormat != dm_444_32) {
		CalculateWriteBackDelay =
				dml_max(
						CalculateWriteBackDelay,
						dml_max(
								dml_ceil(
										WritebackChromaHTaps
												/ 2.0,
										1)
										/ (2
												* WritebackHRatio),
								WritebackChromaVTaps
										* dml_ceil(
												1
														/ (2
																* WritebackVRatio),
												1)
										* dml_ceil(
												WritebackDestinationWidth
														/ 2.0
														/ 2.0,
												1)
										+ dml_ceil(
												1
														/ (2
																* WritebackVRatio),
												1)
												* (dml_ceil(
														WritebackChromaVTaps
																/ 4.0,
														1)
														+ 4)));
	}
	return CalculateWriteBackDelay;
}