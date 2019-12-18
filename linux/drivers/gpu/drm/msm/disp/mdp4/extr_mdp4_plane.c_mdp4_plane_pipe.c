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
struct mdp4_plane {int pipe; } ;
struct drm_plane {int dummy; } ;
typedef  enum mdp4_pipe { ____Placeholder_mdp4_pipe } mdp4_pipe ;

/* Variables and functions */
 struct mdp4_plane* to_mdp4_plane (struct drm_plane*) ; 

enum mdp4_pipe mdp4_plane_pipe(struct drm_plane *plane)
{
	struct mdp4_plane *mdp4_plane = to_mdp4_plane(plane);
	return mdp4_plane->pipe;
}