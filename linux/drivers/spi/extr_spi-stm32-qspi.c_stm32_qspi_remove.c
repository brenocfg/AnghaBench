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
struct stm32_qspi {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct stm32_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stm32_qspi_release (struct stm32_qspi*) ; 

__attribute__((used)) static int stm32_qspi_remove(struct platform_device *pdev)
{
	struct stm32_qspi *qspi = platform_get_drvdata(pdev);

	stm32_qspi_release(qspi);
	return 0;
}