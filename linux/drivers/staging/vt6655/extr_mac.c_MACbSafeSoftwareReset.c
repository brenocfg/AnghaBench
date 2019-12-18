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
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int MAC_MAX_CONTEXT_SIZE_PAGE0 ; 
 int MAC_MAX_CONTEXT_SIZE_PAGE1 ; 
 int MACbSoftwareReset (struct vnt_private*) ; 
 int /*<<< orphan*/  MACvRestoreContext (struct vnt_private*,unsigned char*) ; 
 int /*<<< orphan*/  MACvSaveContext (struct vnt_private*,unsigned char*) ; 

bool MACbSafeSoftwareReset(struct vnt_private *priv)
{
	unsigned char abyTmpRegData[MAC_MAX_CONTEXT_SIZE_PAGE0 + MAC_MAX_CONTEXT_SIZE_PAGE1];
	bool bRetVal;

	/* PATCH....
	 * save some important register's value, then do
	 * reset, then restore register's value
	 */
	/* save MAC context */
	MACvSaveContext(priv, abyTmpRegData);
	/* do reset */
	bRetVal = MACbSoftwareReset(priv);
	/* restore MAC context, except CR0 */
	MACvRestoreContext(priv, abyTmpRegData);

	return bRetVal;
}