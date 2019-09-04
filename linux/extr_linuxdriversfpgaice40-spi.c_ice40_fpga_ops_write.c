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
struct ice40_fpga_priv {int /*<<< orphan*/  dev; } ;
struct fpga_manager {struct ice40_fpga_priv* priv; } ;

/* Variables and functions */
 int spi_write (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int ice40_fpga_ops_write(struct fpga_manager *mgr,
				const char *buf, size_t count)
{
	struct ice40_fpga_priv *priv = mgr->priv;

	return spi_write(priv->dev, buf, count);
}