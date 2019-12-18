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
typedef  int u8 ;
struct st_nci_spi_phy {TYPE_1__* ndlc; struct spi_device* spi_dev; } ;
struct spi_transfer {int* rx_buf; int len; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct sk_buff {int data; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int hard_fault; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ST_NCI_SPI_MAX_SIZE ; 
 int ST_NCI_SPI_MIN_SIZE ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int,int*,int) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int spi_sync_transfer (struct spi_device*,struct spi_transfer*,int) ; 

__attribute__((used)) static int st_nci_spi_read(struct st_nci_spi_phy *phy,
			struct sk_buff **skb)
{
	int r;
	u8 len;
	u8 buf[ST_NCI_SPI_MAX_SIZE];
	struct spi_device *dev = phy->spi_dev;
	struct spi_transfer spi_xfer = {
		.rx_buf = buf,
		.len = ST_NCI_SPI_MIN_SIZE,
	};

	r = spi_sync_transfer(dev, &spi_xfer, 1);
	if (r < 0)
		return -EREMOTEIO;

	len = be16_to_cpu(*(__be16 *) (buf + 2));
	if (len > ST_NCI_SPI_MAX_SIZE) {
		nfc_err(&dev->dev, "invalid frame len\n");
		phy->ndlc->hard_fault = 1;
		return -EBADMSG;
	}

	*skb = alloc_skb(ST_NCI_SPI_MIN_SIZE + len, GFP_KERNEL);
	if (*skb == NULL)
		return -ENOMEM;

	skb_reserve(*skb, ST_NCI_SPI_MIN_SIZE);
	skb_put(*skb, ST_NCI_SPI_MIN_SIZE);
	memcpy((*skb)->data, buf, ST_NCI_SPI_MIN_SIZE);

	if (!len)
		return 0;

	spi_xfer.len = len;
	r = spi_sync_transfer(dev, &spi_xfer, 1);
	if (r < 0) {
		kfree_skb(*skb);
		return -EREMOTEIO;
	}

	skb_put(*skb, len);
	memcpy((*skb)->data + ST_NCI_SPI_MIN_SIZE, buf, len);

	return 0;
}