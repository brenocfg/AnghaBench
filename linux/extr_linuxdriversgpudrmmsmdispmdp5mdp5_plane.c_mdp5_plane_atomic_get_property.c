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
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_drm_private {struct drm_property** plane_property; } ;
struct mdp5_plane_state {int /*<<< orphan*/  zpos; } ;
struct drm_property {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 size_t PLANE_PROP_ZPOS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mdp5_plane_state* to_mdp5_plane_state (struct drm_plane_state const*) ; 

__attribute__((used)) static int mdp5_plane_atomic_get_property(struct drm_plane *plane,
		const struct drm_plane_state *state,
		struct drm_property *property, uint64_t *val)
{
	struct drm_device *dev = plane->dev;
	struct mdp5_plane_state *pstate;
	struct msm_drm_private *dev_priv = dev->dev_private;
	int ret = 0;

	pstate = to_mdp5_plane_state(state);

#define GET_PROPERTY(name, NAME, type) do { \
		if (dev_priv->plane_property[PLANE_PROP_##NAME] == property) { \
			*val = pstate->name; \
			DBG("Get property %s %lld", #name, *val); \
			goto done; \
		} \
	} while (0)

	GET_PROPERTY(zpos, ZPOS, uint8_t);

	dev_err(dev->dev, "Invalid property\n");
	ret = -EINVAL;
done:
	return ret;
#undef SET_PROPERTY
}