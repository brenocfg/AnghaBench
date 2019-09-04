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
struct pcf50633_adc {int dummy; } ;
struct pcf50633 {int /*<<< orphan*/  adc_pdev; } ;

/* Variables and functions */
 struct pcf50633_adc* platform_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct pcf50633_adc *__to_adc(struct pcf50633 *pcf)
{
	return platform_get_drvdata(pcf->adc_pdev);
}