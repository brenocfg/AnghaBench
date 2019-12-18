#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct nvmem_device {int dummy; } ;
struct lpc18xx_otp {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {struct lpc18xx_otp* priv; int /*<<< orphan*/ * dev; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC18XX_OTP_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct nvmem_device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct lpc18xx_otp* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ lpc18xx_otp_nvmem_config ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc18xx_otp_probe(struct platform_device *pdev)
{
	struct nvmem_device *nvmem;
	struct lpc18xx_otp *otp;
	struct resource *res;

	otp = devm_kzalloc(&pdev->dev, sizeof(*otp), GFP_KERNEL);
	if (!otp)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	otp->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(otp->base))
		return PTR_ERR(otp->base);

	lpc18xx_otp_nvmem_config.size = LPC18XX_OTP_SIZE;
	lpc18xx_otp_nvmem_config.dev = &pdev->dev;
	lpc18xx_otp_nvmem_config.priv = otp;

	nvmem = devm_nvmem_register(&pdev->dev, &lpc18xx_otp_nvmem_config);

	return PTR_ERR_OR_ZERO(nvmem);
}