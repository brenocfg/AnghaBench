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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct qcaspi {scalar_t__ burst_len; scalar_t__ legacy_mode; } ;

/* Variables and functions */
 int QCA7K_SPI_EXTERNAL ; 
 int QCA7K_SPI_WRITE ; 
 int /*<<< orphan*/  SPI_REG_BFR_SIZE ; 
 int /*<<< orphan*/  qcaspi_tx_cmd (struct qcaspi*,int) ; 
 scalar_t__ qcaspi_write_burst (struct qcaspi*,scalar_t__,scalar_t__) ; 
 scalar_t__ qcaspi_write_legacy (struct qcaspi*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qcaspi_write_register (struct qcaspi*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_verify ; 

__attribute__((used)) static int
qcaspi_tx_frame(struct qcaspi *qca, struct sk_buff *skb)
{
	u32 count;
	u32 written;
	u32 offset;
	u32 len;

	len = skb->len;

	qcaspi_write_register(qca, SPI_REG_BFR_SIZE, len, wr_verify);
	if (qca->legacy_mode)
		qcaspi_tx_cmd(qca, QCA7K_SPI_WRITE | QCA7K_SPI_EXTERNAL);

	offset = 0;
	while (len) {
		count = len;
		if (count > qca->burst_len)
			count = qca->burst_len;

		if (qca->legacy_mode) {
			written = qcaspi_write_legacy(qca,
						      skb->data + offset,
						      count);
		} else {
			written = qcaspi_write_burst(qca,
						     skb->data + offset,
						     count);
		}

		if (written != count)
			return -1;

		offset += count;
		len -= count;
	}

	return 0;
}