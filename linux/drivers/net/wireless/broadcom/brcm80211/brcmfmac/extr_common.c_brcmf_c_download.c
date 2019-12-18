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
typedef  int u16 ;
struct brcmf_if {int dummy; } ;
struct brcmf_dload_data_le {void* crc; void* len; void* dload_type; void* flag; } ;
typedef  int s32 ;

/* Variables and functions */
 int DLOAD_FLAG_VER_SHIFT ; 
 int DLOAD_HANDLER_VER ; 
 int DL_TYPE_CLM ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_dload_data_le*,scalar_t__) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 

__attribute__((used)) static int brcmf_c_download(struct brcmf_if *ifp, u16 flag,
			    struct brcmf_dload_data_le *dload_buf,
			    u32 len)
{
	s32 err;

	flag |= (DLOAD_HANDLER_VER << DLOAD_FLAG_VER_SHIFT);
	dload_buf->flag = cpu_to_le16(flag);
	dload_buf->dload_type = cpu_to_le16(DL_TYPE_CLM);
	dload_buf->len = cpu_to_le32(len);
	dload_buf->crc = cpu_to_le32(0);
	len = sizeof(*dload_buf) + len - 1;

	err = brcmf_fil_iovar_data_set(ifp, "clmload", dload_buf, len);

	return err;
}