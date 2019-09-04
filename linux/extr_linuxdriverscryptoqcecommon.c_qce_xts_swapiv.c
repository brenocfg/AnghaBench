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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int QCE_AES_IV_LENGTH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qce_cpu_to_be32p_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qce_xts_swapiv(__be32 *dst, const u8 *src, unsigned int ivsize)
{
	u8 swap[QCE_AES_IV_LENGTH];
	u32 i, j;

	if (ivsize > QCE_AES_IV_LENGTH)
		return;

	memset(swap, 0, QCE_AES_IV_LENGTH);

	for (i = (QCE_AES_IV_LENGTH - ivsize), j = ivsize - 1;
	     i < QCE_AES_IV_LENGTH; i++, j--)
		swap[i] = src[j];

	qce_cpu_to_be32p_array(dst, swap, QCE_AES_IV_LENGTH);
}