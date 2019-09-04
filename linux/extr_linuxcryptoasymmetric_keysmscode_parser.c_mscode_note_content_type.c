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
typedef  enum OID { ____Placeholder_OID } OID ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int EBADMSG ; 
 int OID__NR ; 
 int OID_msIndividualSPKeyPurpose ; 
 int OID_msPeImageDataObjId ; 
 int look_up_OID (void const*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sprint_oid (void const*,size_t,char*,int) ; 

int mscode_note_content_type(void *context, size_t hdrlen,
			     unsigned char tag,
			     const void *value, size_t vlen)
{
	enum OID oid;

	oid = look_up_OID(value, vlen);
	if (oid == OID__NR) {
		char buffer[50];

		sprint_oid(value, vlen, buffer, sizeof(buffer));
		pr_err("Unknown OID: %s\n", buffer);
		return -EBADMSG;
	}

	/*
	 * pesign utility had a bug where it was putting
	 * OID_msIndividualSPKeyPurpose instead of OID_msPeImageDataObjId
	 * So allow both OIDs.
	 */
	if (oid != OID_msPeImageDataObjId &&
	    oid != OID_msIndividualSPKeyPurpose) {
		pr_err("Unexpected content type OID %u\n", oid);
		return -EBADMSG;
	}

	return 0;
}