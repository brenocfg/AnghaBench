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
struct soc_pcmcia_socket {scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpac270_cf_gpios ; 
 int /*<<< orphan*/  vpac270_pcmcia_gpios ; 

__attribute__((used)) static void vpac270_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	if (skt->nr == 0)
		gpio_free_array(vpac270_pcmcia_gpios,
					ARRAY_SIZE(vpac270_pcmcia_gpios));
	else
		gpio_free_array(vpac270_cf_gpios,
					ARRAY_SIZE(vpac270_cf_gpios));
}