#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;
struct soc_pcmcia_socket {struct max1600* driver_data; scalar_t__ nr; int /*<<< orphan*/  gpio_reset; TYPE_3__* stat; TYPE_2__ socket; } ;
struct max1600 {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX1600_CHAN_A ; 
 int /*<<< orphan*/  MAX1600_CHAN_B ; 
 int /*<<< orphan*/  MAX1600_CODE_HIGH ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t SOC_STAT_BVD1 ; 
 size_t SOC_STAT_BVD2 ; 
 size_t SOC_STAT_CD ; 
 size_t SOC_STAT_RDY ; 
 size_t SOC_STAT_VS1 ; 
 size_t SOC_STAT_VS2 ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int max1600_init (struct device*,struct max1600**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int soc_pcmcia_request_gpiods (struct soc_pcmcia_socket*) ; 

__attribute__((used)) static int mst_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	struct device *dev = skt->socket.dev.parent;
	struct max1600 *m;
	int ret;

	skt->stat[SOC_STAT_CD].name = skt->nr ? "bdetect" : "adetect";
	skt->stat[SOC_STAT_BVD1].name = skt->nr ? "bbvd1" : "abvd1";
	skt->stat[SOC_STAT_BVD2].name = skt->nr ? "bbvd2" : "abvd2";
	skt->stat[SOC_STAT_RDY].name = skt->nr ? "bready" : "aready";
	skt->stat[SOC_STAT_VS1].name = skt->nr ? "bvs1" : "avs1";
	skt->stat[SOC_STAT_VS2].name = skt->nr ? "bvs2" : "avs2";

	skt->gpio_reset = devm_gpiod_get(dev, skt->nr ? "breset" : "areset",
					 GPIOD_OUT_HIGH);
	if (IS_ERR(skt->gpio_reset))
		return PTR_ERR(skt->gpio_reset);

	ret = max1600_init(dev, &m, skt->nr ? MAX1600_CHAN_B : MAX1600_CHAN_A,
			   MAX1600_CODE_HIGH);
	if (ret)
		return ret;

	skt->driver_data = m;

	return soc_pcmcia_request_gpiods(skt);
}