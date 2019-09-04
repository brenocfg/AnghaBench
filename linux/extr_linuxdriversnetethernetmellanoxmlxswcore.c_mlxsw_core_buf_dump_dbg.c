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
struct mlxsw_core {TYPE_1__* bus_info; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_core_buf_dump_dbg(struct mlxsw_core *mlxsw_core,
				    const char *buf, size_t size)
{
	__be32 *m = (__be32 *) buf;
	int i;
	int count = size / sizeof(__be32);

	for (i = count - 1; i >= 0; i--)
		if (m[i])
			break;
	i++;
	count = i ? i : 1;
	for (i = 0; i < count; i += 4)
		dev_dbg(mlxsw_core->bus_info->dev, "%04x - %08x %08x %08x %08x\n",
			i * 4, be32_to_cpu(m[i]), be32_to_cpu(m[i + 1]),
			be32_to_cpu(m[i + 2]), be32_to_cpu(m[i + 3]));
}