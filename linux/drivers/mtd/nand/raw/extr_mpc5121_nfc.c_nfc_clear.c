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
typedef  int /*<<< orphan*/  uint ;
typedef  int u16 ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int nfc_read (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_write (struct mtd_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void nfc_clear(struct mtd_info *mtd, uint reg, u16 bits)
{
	nfc_write(mtd, reg, nfc_read(mtd, reg) & ~bits);
}