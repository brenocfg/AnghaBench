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
typedef  int u8 ;
typedef  int u16 ;
struct saa7134_go7007 {struct saa7134_dev* dev; } ;
struct saa7134_dev {int dummy; } ;
struct go7007 {struct saa7134_go7007* hpi_context; } ;

/* Variables and functions */
 int GPIO_COMMAND_ADDR ; 
 int GPIO_COMMAND_IDLE ; 
 int GPIO_COMMAND_WRITE ; 
 int HPI_ADDR_INIT_BUFFER ; 
 int /*<<< orphan*/  HPI_ADDR_INTR_STATUS ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS2 ; 
 int /*<<< orphan*/  gpio_read (struct saa7134_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int saa7134_go7007_send_firmware(struct go7007 *go, u8 *data, int len)
{
	struct saa7134_go7007 *saa = go->hpi_context;
	struct saa7134_dev *dev = saa->dev;
	u16 status_reg;
	int i;

#ifdef GO7007_HPI_DEBUG
	pr_debug("saa7134-go7007: DownloadBuffer sending %d bytes\n", len);
#endif

	while (len > 0) {
		i = len > 64 ? 64 : len;
		saa_writeb(SAA7134_GPIO_GPMODE0, 0xff);
		saa_writeb(SAA7134_GPIO_GPSTATUS0, HPI_ADDR_INIT_BUFFER);
		saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDR);
		saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);
		while (i-- > 0) {
			saa_writeb(SAA7134_GPIO_GPSTATUS0, *data);
			saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WRITE);
			saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);
			++data;
			--len;
		}
		for (i = 0; i < 100; ++i) {
			gpio_read(dev, HPI_ADDR_INTR_STATUS, &status_reg);
			if (!(status_reg & 0x0002))
				break;
		}
		if (i == 100) {
			pr_err("saa7134-go7007: device is hung, status reg = 0x%04x\n",
			       status_reg);
			return -1;
		}
	}
	return 0;
}