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
struct s5p_cec_dev {int /*<<< orphan*/  dev; scalar_t__ reg; } ;

/* Variables and functions */
 char CEC_MESSAGE_BROADCAST ; 
 char CEC_MESSAGE_BROADCAST_MASK ; 
 scalar_t__ S5P_CEC_TX_BUFF0 ; 
 scalar_t__ S5P_CEC_TX_BYTES ; 
 scalar_t__ S5P_CEC_TX_CTRL ; 
 int S5P_CEC_TX_CTRL_BCAST ; 
 int S5P_CEC_TX_CTRL_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

void s5p_cec_copy_packet(struct s5p_cec_dev *cec, char *data,
			 size_t count, u8 retries)
{
	int i = 0;
	u8 reg;

	while (i < count) {
		writeb(data[i], cec->reg + (S5P_CEC_TX_BUFF0 + (i * 4)));
		i++;
	}

	writeb(count, cec->reg + S5P_CEC_TX_BYTES);
	reg = readb(cec->reg + S5P_CEC_TX_CTRL);
	reg |= S5P_CEC_TX_CTRL_START;
	reg &= ~0x70;
	reg |= retries << 4;

	if ((data[0] & CEC_MESSAGE_BROADCAST_MASK) == CEC_MESSAGE_BROADCAST) {
		dev_dbg(cec->dev, "Broadcast");
		reg |= S5P_CEC_TX_CTRL_BCAST;
	} else {
		dev_dbg(cec->dev, "No Broadcast");
		reg &= ~S5P_CEC_TX_CTRL_BCAST;
	}

	writeb(reg, cec->reg + S5P_CEC_TX_CTRL);
	dev_dbg(cec->dev, "cec-tx: cec count (%zu): %*ph", count,
		(int)count, data);
}