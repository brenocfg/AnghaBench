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
struct edid {int dummy; } ;
struct drm_connector {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct edid* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* edid_firmware ; 
 struct edid* edid_load (struct drm_connector*,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strsep (char**,char*) ; 

struct edid *drm_load_edid_firmware(struct drm_connector *connector)
{
	const char *connector_name = connector->name;
	char *edidname, *last, *colon, *fwstr, *edidstr, *fallback = NULL;
	struct edid *edid;

	if (edid_firmware[0] == '\0')
		return ERR_PTR(-ENOENT);

	/*
	 * If there are multiple edid files specified and separated
	 * by commas, search through the list looking for one that
	 * matches the connector.
	 *
	 * If there's one or more that doesn't specify a connector, keep
	 * the last one found one as a fallback.
	 */
	fwstr = kstrdup(edid_firmware, GFP_KERNEL);
	if (!fwstr)
		return ERR_PTR(-ENOMEM);
	edidstr = fwstr;

	while ((edidname = strsep(&edidstr, ","))) {
		colon = strchr(edidname, ':');
		if (colon != NULL) {
			if (strncmp(connector_name, edidname, colon - edidname))
				continue;
			edidname = colon + 1;
			break;
		}

		if (*edidname != '\0') /* corner case: multiple ',' */
			fallback = edidname;
	}

	if (!edidname) {
		if (!fallback) {
			kfree(fwstr);
			return ERR_PTR(-ENOENT);
		}
		edidname = fallback;
	}

	last = edidname + strlen(edidname) - 1;
	if (*last == '\n')
		*last = '\0';

	edid = edid_load(connector, edidname, connector_name);
	kfree(fwstr);

	return edid;
}