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
struct spi_transfer {int len; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_test {int transfer_count; int fill_option; int fill_pattern; struct spi_transfer* transfers; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FILL_COUNT_16 140 
#define  FILL_COUNT_24 139 
#define  FILL_COUNT_32 138 
#define  FILL_COUNT_8 137 
#define  FILL_MEMSET_16 136 
#define  FILL_MEMSET_24 135 
#define  FILL_MEMSET_32 134 
#define  FILL_MEMSET_8 133 
#define  FILL_TRANSFER_BYTE_16 132 
#define  FILL_TRANSFER_BYTE_24 131 
#define  FILL_TRANSFER_BYTE_32 130 
#define  FILL_TRANSFER_BYTE_8 129 
#define  FILL_TRANSFER_NUM 128 
 int GET_VALUE_BYTE (int,int,int) ; 
 int /*<<< orphan*/  SPI_TEST_PATTERN_UNWRITTEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int spi_test_fill_pattern(struct spi_device *spi,
				 struct spi_test *test)
{
	struct spi_transfer *xfers = test->transfers;
	u8 *tx_buf;
	size_t count = 0;
	int i, j;

#ifdef __BIG_ENDIAN
#define GET_VALUE_BYTE(value, index, bytes) \
	(value >> (8 * (bytes - 1 - count % bytes)))
#else
#define GET_VALUE_BYTE(value, index, bytes) \
	(value >> (8 * (count % bytes)))
#endif

	/* fill all transfers with the pattern requested */
	for (i = 0; i < test->transfer_count; i++) {
		/* fill rx_buf with SPI_TEST_PATTERN_UNWRITTEN */
		if (xfers[i].rx_buf)
			memset(xfers[i].rx_buf, SPI_TEST_PATTERN_UNWRITTEN,
			       xfers[i].len);
		/* if tx_buf is NULL then skip */
		tx_buf = (u8 *)xfers[i].tx_buf;
		if (!tx_buf)
			continue;
		/* modify all the transfers */
		for (j = 0; j < xfers[i].len; j++, tx_buf++, count++) {
			/* fill tx */
			switch (test->fill_option) {
			case FILL_MEMSET_8:
				*tx_buf = test->fill_pattern;
				break;
			case FILL_MEMSET_16:
				*tx_buf = GET_VALUE_BYTE(test->fill_pattern,
							 count, 2);
				break;
			case FILL_MEMSET_24:
				*tx_buf = GET_VALUE_BYTE(test->fill_pattern,
							 count, 3);
				break;
			case FILL_MEMSET_32:
				*tx_buf = GET_VALUE_BYTE(test->fill_pattern,
							 count, 4);
				break;
			case FILL_COUNT_8:
				*tx_buf = count;
				break;
			case FILL_COUNT_16:
				*tx_buf = GET_VALUE_BYTE(count, count, 2);
				break;
			case FILL_COUNT_24:
				*tx_buf = GET_VALUE_BYTE(count, count, 3);
				break;
			case FILL_COUNT_32:
				*tx_buf = GET_VALUE_BYTE(count, count, 4);
				break;
			case FILL_TRANSFER_BYTE_8:
				*tx_buf = j;
				break;
			case FILL_TRANSFER_BYTE_16:
				*tx_buf = GET_VALUE_BYTE(j, j, 2);
				break;
			case FILL_TRANSFER_BYTE_24:
				*tx_buf = GET_VALUE_BYTE(j, j, 3);
				break;
			case FILL_TRANSFER_BYTE_32:
				*tx_buf = GET_VALUE_BYTE(j, j, 4);
				break;
			case FILL_TRANSFER_NUM:
				*tx_buf = i;
				break;
			default:
				dev_err(&spi->dev,
					"unsupported fill_option: %i\n",
					test->fill_option);
				return -EINVAL;
			}
		}
	}

	return 0;
}