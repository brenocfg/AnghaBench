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
struct ipu_plane {scalar_t__ dp; int /*<<< orphan*/  alpha_ch; int /*<<< orphan*/  ipu_ch; int /*<<< orphan*/  dmfc; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_dmfc_enable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dp_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dp_enable_channel (scalar_t__) ; 
 int /*<<< orphan*/  ipu_idmac_enable_channel (int /*<<< orphan*/ ) ; 
 scalar_t__ ipu_plane_separate_alpha (struct ipu_plane*) ; 

__attribute__((used)) static void ipu_plane_enable(struct ipu_plane *ipu_plane)
{
	if (ipu_plane->dp)
		ipu_dp_enable(ipu_plane->ipu);
	ipu_dmfc_enable_channel(ipu_plane->dmfc);
	ipu_idmac_enable_channel(ipu_plane->ipu_ch);
	if (ipu_plane_separate_alpha(ipu_plane))
		ipu_idmac_enable_channel(ipu_plane->alpha_ch);
	if (ipu_plane->dp)
		ipu_dp_enable_channel(ipu_plane->dp);
}