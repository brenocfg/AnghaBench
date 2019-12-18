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
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static void mlxsw_core_reg_access_cb(struct mlxsw_core *mlxsw_core,
				     char *payload, size_t payload_len,
				     unsigned long cb_priv)
{
	char *orig_payload = (char *) cb_priv;

	memcpy(orig_payload, payload, payload_len);
}