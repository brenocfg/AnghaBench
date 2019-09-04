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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_spi_boardinfo {int dummy; } ;
struct intel_spi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct intel_spi*) ; 
 int PTR_ERR (struct intel_spi*) ; 
 struct intel_spi_boardinfo* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct intel_spi* intel_spi_probe (int /*<<< orphan*/ *,struct resource*,struct intel_spi_boardinfo*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct intel_spi*) ; 

__attribute__((used)) static int intel_spi_platform_probe(struct platform_device *pdev)
{
	struct intel_spi_boardinfo *info;
	struct intel_spi *ispi;
	struct resource *mem;

	info = dev_get_platdata(&pdev->dev);
	if (!info)
		return -EINVAL;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ispi = intel_spi_probe(&pdev->dev, mem, info);
	if (IS_ERR(ispi))
		return PTR_ERR(ispi);

	platform_set_drvdata(pdev, ispi);
	return 0;
}