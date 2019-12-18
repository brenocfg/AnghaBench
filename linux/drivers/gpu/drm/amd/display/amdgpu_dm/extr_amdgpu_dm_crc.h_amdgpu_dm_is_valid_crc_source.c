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
 int AMDGPU_DM_PIPE_CRC_SOURCE_MAX ; 
 int AMDGPU_DM_PIPE_CRC_SOURCE_NONE ; 

__attribute__((used)) static inline bool amdgpu_dm_is_valid_crc_source(enum amdgpu_dm_pipe_crc_source source)
{
	return (source > AMDGPU_DM_PIPE_CRC_SOURCE_NONE) &&
	       (source < AMDGPU_DM_PIPE_CRC_SOURCE_MAX);
}