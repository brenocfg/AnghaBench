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
struct gfar_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfar_configure_coalescing (struct gfar_private*,int,int) ; 

__attribute__((used)) static void gfar_configure_coalescing_all(struct gfar_private *priv)
{
	gfar_configure_coalescing(priv, 0xFF, 0xFF);
}