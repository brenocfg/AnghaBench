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
typedef  int u32 ;
struct atmel_nfc_op {int errors; int wait; } ;

/* Variables and functions */
 int ATMEL_HSMC_NFC_SR_ERRORS ; 

__attribute__((used)) static bool atmel_nfc_op_done(struct atmel_nfc_op *op, u32 status)
{
	op->errors |= status & ATMEL_HSMC_NFC_SR_ERRORS;
	op->wait ^= status & op->wait;

	return !op->wait || op->errors;
}