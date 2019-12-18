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
struct prp_priv {int /*<<< orphan*/  rot_mode; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 scalar_t__ ipu_rot_mode_is_irt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prp_unsetup_norotation (struct prp_priv*) ; 
 int /*<<< orphan*/  prp_unsetup_rotation (struct prp_priv*) ; 
 int /*<<< orphan*/  prp_unsetup_vb2_buf (struct prp_priv*,int) ; 

__attribute__((used)) static void prp_unsetup(struct prp_priv *priv,
			enum vb2_buffer_state state)
{
	if (ipu_rot_mode_is_irt(priv->rot_mode))
		prp_unsetup_rotation(priv);
	else
		prp_unsetup_norotation(priv);

	prp_unsetup_vb2_buf(priv, state);
}