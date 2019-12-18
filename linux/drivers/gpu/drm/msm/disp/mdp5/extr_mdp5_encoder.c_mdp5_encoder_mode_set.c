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
struct mdp5_interface {scalar_t__ mode; } ;
struct mdp5_encoder {struct mdp5_interface* intf; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 scalar_t__ MDP5_INTF_DSI_MODE_COMMAND ; 
 int /*<<< orphan*/  mdp5_cmd_encoder_mode_set (struct drm_encoder*,struct drm_display_mode*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  mdp5_vid_encoder_mode_set (struct drm_encoder*,struct drm_display_mode*,struct drm_display_mode*) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp5_encoder_mode_set(struct drm_encoder *encoder,
				  struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode)
{
	struct mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	struct mdp5_interface *intf = mdp5_encoder->intf;

	if (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encoder_mode_set(encoder, mode, adjusted_mode);
	else
		mdp5_vid_encoder_mode_set(encoder, mode, adjusted_mode);
}