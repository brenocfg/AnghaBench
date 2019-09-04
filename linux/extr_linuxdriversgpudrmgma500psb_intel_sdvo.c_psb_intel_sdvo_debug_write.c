#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct psb_intel_sdvo {int dummy; } ;
struct TYPE_3__ {scalar_t__ cmd; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  SDVO_NAME (struct psb_intel_sdvo*) ; 
 TYPE_1__* sdvo_cmd_names ; 

__attribute__((used)) static void psb_intel_sdvo_debug_write(struct psb_intel_sdvo *psb_intel_sdvo, u8 cmd,
				   const void *args, int args_len)
{
	int i;

	DRM_DEBUG_KMS("%s: W: %02X ",
				SDVO_NAME(psb_intel_sdvo), cmd);
	for (i = 0; i < args_len; i++)
		DRM_DEBUG_KMS("%02X ", ((u8 *)args)[i]);
	for (; i < 8; i++)
		DRM_DEBUG_KMS("   ");
	for (i = 0; i < ARRAY_SIZE(sdvo_cmd_names); i++) {
		if (cmd == sdvo_cmd_names[i].cmd) {
			DRM_DEBUG_KMS("(%s)", sdvo_cmd_names[i].name);
			break;
		}
	}
	if (i == ARRAY_SIZE(sdvo_cmd_names))
		DRM_DEBUG_KMS("(%02X)", cmd);
	DRM_DEBUG_KMS("\n");
}