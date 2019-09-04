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
typedef  int /*<<< orphan*/  u16 ;
struct drm_crtc {int gamma_size; int /*<<< orphan*/ * gamma_store; int /*<<< orphan*/  enabled; TYPE_1__* dev; } ;
struct ast_private {int dummy; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_load_palette_index (struct ast_private*,int,int,int,int) ; 

__attribute__((used)) static void ast_crtc_load_lut(struct drm_crtc *crtc)
{
	struct ast_private *ast = crtc->dev->dev_private;
	u16 *r, *g, *b;
	int i;

	if (!crtc->enabled)
		return;

	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;

	for (i = 0; i < 256; i++)
		ast_load_palette_index(ast, i, *r++ >> 8, *g++ >> 8, *b++ >> 8);
}