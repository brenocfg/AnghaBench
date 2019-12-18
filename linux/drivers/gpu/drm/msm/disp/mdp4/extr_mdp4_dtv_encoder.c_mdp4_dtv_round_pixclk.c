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
struct mdp4_dtv_encoder {int /*<<< orphan*/  mdp_clk; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 long clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct mdp4_dtv_encoder* to_mdp4_dtv_encoder (struct drm_encoder*) ; 

long mdp4_dtv_round_pixclk(struct drm_encoder *encoder, unsigned long rate)
{
	struct mdp4_dtv_encoder *mdp4_dtv_encoder = to_mdp4_dtv_encoder(encoder);
	return clk_round_rate(mdp4_dtv_encoder->mdp_clk, rate);
}