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
typedef  char s8 ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  bsscfgidx_le ;
typedef  char __le32 ;

/* Variables and functions */
 scalar_t__ brcmf_create_iovar (char*,char*,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 char cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static u32
brcmf_create_bsscfg(s32 bsscfgidx, char *name, char *data, u32 datalen,
		    char *buf, u32 buflen)
{
	const s8 *prefix = "bsscfg:";
	s8 *p;
	u32 prefixlen;
	u32 namelen;
	u32 iolen;
	__le32 bsscfgidx_le;

	if (bsscfgidx == 0)
		return brcmf_create_iovar(name, data, datalen, buf, buflen);

	prefixlen = strlen(prefix);
	namelen = strlen(name) + 1; /* length of iovar  name + null */
	iolen = prefixlen + namelen + sizeof(bsscfgidx_le) + datalen;

	if (buflen < iolen) {
		brcmf_err("buffer is too short\n");
		return 0;
	}

	p = buf;

	/* copy prefix, no null */
	memcpy(p, prefix, prefixlen);
	p += prefixlen;

	/* copy iovar name including null */
	memcpy(p, name, namelen);
	p += namelen;

	/* bss config index as first data */
	bsscfgidx_le = cpu_to_le32(bsscfgidx);
	memcpy(p, &bsscfgidx_le, sizeof(bsscfgidx_le));
	p += sizeof(bsscfgidx_le);

	/* parameter buffer follows */
	if (datalen)
		memcpy(p, data, datalen);

	return iolen;
}