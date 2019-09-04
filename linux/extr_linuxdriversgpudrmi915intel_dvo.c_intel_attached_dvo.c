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
struct intel_dvo {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct intel_dvo* enc_to_dvo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_attached_encoder (struct drm_connector*) ; 

__attribute__((used)) static struct intel_dvo *intel_attached_dvo(struct drm_connector *connector)
{
	return enc_to_dvo(intel_attached_encoder(connector));
}