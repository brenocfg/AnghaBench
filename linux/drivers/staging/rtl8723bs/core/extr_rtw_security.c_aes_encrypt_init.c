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
typedef  void u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AES_PRIV_SIZE ; 
 int /*<<< orphan*/  rijndaelKeySetupEnc (void*,int /*<<< orphan*/ *) ; 
 void* rtw_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *aes_encrypt_init(u8 *key, size_t len)
{
	u32 *rk;
	if (len != 16)
		return NULL;
	rk = rtw_malloc(AES_PRIV_SIZE);
	if (rk == NULL)
		return NULL;
	rijndaelKeySetupEnc(rk, key);
	return rk;
}