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
struct ipu_plane {int /*<<< orphan*/  alpha_ch; int /*<<< orphan*/  ipu_ch; int /*<<< orphan*/  dmfc; int /*<<< orphan*/  dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dmfc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dp_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_put (int /*<<< orphan*/ ) ; 

void ipu_plane_put_resources(struct ipu_plane *ipu_plane)
{
	if (!IS_ERR_OR_NULL(ipu_plane->dp))
		ipu_dp_put(ipu_plane->dp);
	if (!IS_ERR_OR_NULL(ipu_plane->dmfc))
		ipu_dmfc_put(ipu_plane->dmfc);
	if (!IS_ERR_OR_NULL(ipu_plane->ipu_ch))
		ipu_idmac_put(ipu_plane->ipu_ch);
	if (!IS_ERR_OR_NULL(ipu_plane->alpha_ch))
		ipu_idmac_put(ipu_plane->alpha_ch);
}