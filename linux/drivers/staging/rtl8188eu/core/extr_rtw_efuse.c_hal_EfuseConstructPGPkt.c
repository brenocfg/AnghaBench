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
typedef  void* u8 ;
struct pgpkt {void* word_en; int /*<<< orphan*/  word_cnts; scalar_t__ data; void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  Efuse_CalculateWordCnts (void*) ; 
 int /*<<< orphan*/  efuse_WordEnableDataRead (void*,void**,scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 

__attribute__((used)) static void hal_EfuseConstructPGPkt(u8 offset, u8 word_en, u8 *pData, struct pgpkt *pTargetPkt)
{
	memset((void *)pTargetPkt->data, 0xFF, sizeof(u8) * 8);
	pTargetPkt->offset = offset;
	pTargetPkt->word_en = word_en;
	efuse_WordEnableDataRead(word_en, pData, pTargetPkt->data);
	pTargetPkt->word_cnts = Efuse_CalculateWordCnts(pTargetPkt->word_en);
}