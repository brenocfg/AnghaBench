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
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_en_priv {int dummy; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int) ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_info (struct mlx4_en_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speed2ptys_link_modes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 speed_set_ptys_admin(struct mlx4_en_priv *priv, u32 speed,
				   __be32 proto_cap)
{
	__be32 proto_admin = 0;

	if (!speed) { /* Speed = 0 ==> Reset Link modes */
		proto_admin = proto_cap;
		en_info(priv, "Speed was set to 0, Reset advertised Link Modes to default (%x)\n",
			be32_to_cpu(proto_cap));
	} else {
		u32 ptys_link_modes = speed2ptys_link_modes(speed);

		proto_admin = cpu_to_be32(ptys_link_modes) & proto_cap;
		en_info(priv, "Setting Speed to %d\n", speed);
	}
	return proto_admin;
}