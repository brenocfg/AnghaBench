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
 int AMDGPU_DM_PIPE_CRC_SOURCE_DPRX ; 
 int AMDGPU_DM_PIPE_CRC_SOURCE_DPRX_DITHER ; 
 int AMDGPU_DM_PIPE_CRC_SOURCE_INVALID ; 
 int AMDGPU_DM_PIPE_CRC_SOURCE_NONE ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum amdgpu_dm_pipe_crc_source dm_parse_crc_source(const char *source)
{
	if (!source || !strcmp(source, "none"))
		return AMDGPU_DM_PIPE_CRC_SOURCE_NONE;
	if (!strcmp(source, "auto") || !strcmp(source, "crtc"))
		return AMDGPU_DM_PIPE_CRC_SOURCE_CRTC;
	if (!strcmp(source, "dprx"))
		return AMDGPU_DM_PIPE_CRC_SOURCE_DPRX;
	if (!strcmp(source, "crtc dither"))
		return AMDGPU_DM_PIPE_CRC_SOURCE_CRTC_DITHER;
	if (!strcmp(source, "dprx dither"))
		return AMDGPU_DM_PIPE_CRC_SOURCE_DPRX_DITHER;

	return AMDGPU_DM_PIPE_CRC_SOURCE_INVALID;
}