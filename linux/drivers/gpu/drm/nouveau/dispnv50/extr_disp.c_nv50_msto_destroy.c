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
struct nv50_msto {int /*<<< orphan*/  encoder; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nv50_msto*) ; 
 struct nv50_msto* nv50_msto (struct drm_encoder*) ; 

__attribute__((used)) static void
nv50_msto_destroy(struct drm_encoder *encoder)
{
	struct nv50_msto *msto = nv50_msto(encoder);
	drm_encoder_cleanup(&msto->encoder);
	kfree(msto);
}