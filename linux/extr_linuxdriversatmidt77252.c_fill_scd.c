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
struct scq_info {int paddr; scalar_t__ scd; } ;
struct idt77252_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,scalar_t__,int) ; 

__attribute__((used)) static void
fill_scd(struct idt77252_dev *card, struct scq_info *scq, int class)
{
	write_sram(card, scq->scd, scq->paddr);
	write_sram(card, scq->scd + 1, 0x00000000);
	write_sram(card, scq->scd + 2, 0xffffffff);
	write_sram(card, scq->scd + 3, 0x00000000);
}