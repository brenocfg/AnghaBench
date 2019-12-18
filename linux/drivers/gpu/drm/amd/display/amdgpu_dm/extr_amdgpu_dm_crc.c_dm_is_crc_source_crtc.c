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
typedef  enum amdgpu_dm_pipe_crc_source { ____Placeholder_amdgpu_dm_pipe_crc_source } amdgpu_dm_pipe_crc_source ;

/* Variables and functions */
 int AMDGPU_DM_PIPE_CRC_SOURCE_CRTC ; 
 int AMDGPU_DM_PIPE_CRC_SOURCE_CRTC_DITHER ; 

__attribute__((used)) static bool dm_is_crc_source_crtc(enum amdgpu_dm_pipe_crc_source src)
{
	return (src == AMDGPU_DM_PIPE_CRC_SOURCE_CRTC) ||
	       (src == AMDGPU_DM_PIPE_CRC_SOURCE_CRTC_DITHER);
}