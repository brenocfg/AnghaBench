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
struct mdp5_kms {int dummy; } ;
struct mdp5_encoder {TYPE_1__* intf; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MDP5_INTF_LINE_COUNT (int) ; 
 struct mdp5_kms* get_kms (struct drm_encoder*) ; 
 int mdp5_read (struct mdp5_kms*,int /*<<< orphan*/ ) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

int mdp5_encoder_get_linecount(struct drm_encoder *encoder)
{
	struct mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	struct mdp5_kms *mdp5_kms = get_kms(encoder);
	int intf = mdp5_encoder->intf->num;

	return mdp5_read(mdp5_kms, REG_MDP5_INTF_LINE_COUNT(intf));
}