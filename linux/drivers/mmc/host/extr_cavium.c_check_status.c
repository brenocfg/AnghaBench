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
typedef  int u64 ;

/* Variables and functions */
 int EILSEQ ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int MIO_EMM_RSP_STS_BLK_CRC_ERR ; 
 int MIO_EMM_RSP_STS_BLK_TIMEOUT ; 
 int MIO_EMM_RSP_STS_DBUF_ERR ; 
 int MIO_EMM_RSP_STS_RSP_BAD_STS ; 
 int MIO_EMM_RSP_STS_RSP_CRC_ERR ; 
 int MIO_EMM_RSP_STS_RSP_TIMEOUT ; 

__attribute__((used)) static int check_status(u64 rsp_sts)
{
	if (rsp_sts & MIO_EMM_RSP_STS_RSP_BAD_STS ||
	    rsp_sts & MIO_EMM_RSP_STS_RSP_CRC_ERR ||
	    rsp_sts & MIO_EMM_RSP_STS_BLK_CRC_ERR)
		return -EILSEQ;
	if (rsp_sts & MIO_EMM_RSP_STS_RSP_TIMEOUT ||
	    rsp_sts & MIO_EMM_RSP_STS_BLK_TIMEOUT)
		return -ETIMEDOUT;
	if (rsp_sts & MIO_EMM_RSP_STS_DBUF_ERR)
		return -EIO;
	return 0;
}