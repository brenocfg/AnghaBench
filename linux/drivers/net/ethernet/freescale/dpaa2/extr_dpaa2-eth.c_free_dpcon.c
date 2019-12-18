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
struct fsl_mc_device {int /*<<< orphan*/  mc_handle; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpcon_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpcon_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_mc_object_free (struct fsl_mc_device*) ; 

__attribute__((used)) static void free_dpcon(struct dpaa2_eth_priv *priv,
		       struct fsl_mc_device *dpcon)
{
	dpcon_disable(priv->mc_io, 0, dpcon->mc_handle);
	dpcon_close(priv->mc_io, 0, dpcon->mc_handle);
	fsl_mc_object_free(dpcon);
}