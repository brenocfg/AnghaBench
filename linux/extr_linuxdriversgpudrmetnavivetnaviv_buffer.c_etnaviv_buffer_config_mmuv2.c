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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int features; } ;
struct etnaviv_cmdbuf {int user_size; } ;
struct etnaviv_gpu {TYPE_1__ identity; int /*<<< orphan*/  lock; struct etnaviv_cmdbuf buffer; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  CMD_END (struct etnaviv_cmdbuf*) ; 
 int /*<<< orphan*/  CMD_LOAD_STATE (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMD_SEM (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_STALL (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETNA_PIPE_2D ; 
 int /*<<< orphan*/  ETNA_PIPE_3D ; 
 int /*<<< orphan*/  SYNC_RECIPIENT_FE ; 
 int /*<<< orphan*/  SYNC_RECIPIENT_PE ; 
 int /*<<< orphan*/  VIVS_GL_PIPE_SELECT ; 
 int VIVS_GL_PIPE_SELECT_PIPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIVS_MMUv2_CONFIGURATION ; 
 int VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K ; 
 int /*<<< orphan*/  VIVS_MMUv2_SAFE_ADDRESS ; 
 int chipFeatures_PIPE_2D ; 
 int chipFeatures_PIPE_3D ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

u16 etnaviv_buffer_config_mmuv2(struct etnaviv_gpu *gpu, u32 mtlb_addr, u32 safe_addr)
{
	struct etnaviv_cmdbuf *buffer = &gpu->buffer;

	lockdep_assert_held(&gpu->lock);

	buffer->user_size = 0;

	if (gpu->identity.features & chipFeatures_PIPE_3D) {
		CMD_LOAD_STATE(buffer, VIVS_GL_PIPE_SELECT,
			       VIVS_GL_PIPE_SELECT_PIPE(ETNA_PIPE_3D));
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_CONFIGURATION,
			mtlb_addr | VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K);
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_SAFE_ADDRESS, safe_addr);
		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	}

	if (gpu->identity.features & chipFeatures_PIPE_2D) {
		CMD_LOAD_STATE(buffer, VIVS_GL_PIPE_SELECT,
			       VIVS_GL_PIPE_SELECT_PIPE(ETNA_PIPE_2D));
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_CONFIGURATION,
			mtlb_addr | VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K);
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_SAFE_ADDRESS, safe_addr);
		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	}

	CMD_END(buffer);

	buffer->user_size = ALIGN(buffer->user_size, 8);

	return buffer->user_size / 8;
}