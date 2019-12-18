#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_params {int /*<<< orphan*/  no_hwmon; int /*<<< orphan*/  governor_name; } ;
struct thermal_zone_device_ops {scalar_t__ (* get_trip_temp ) (struct thermal_zone_device*,int,int*) ;scalar_t__ (* get_trip_type ) (struct thermal_zone_device*,int,int*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * class; } ;
struct thermal_zone_device {int id; int trips; int passive_delay; int polling_delay; TYPE_1__ device; int /*<<< orphan*/  need_update; int /*<<< orphan*/  poll_queue; int /*<<< orphan*/  node; struct thermal_zone_params* tzp; int /*<<< orphan*/  trips_disabled; struct thermal_zone_device_ops* ops; void* devdata; int /*<<< orphan*/  type; int /*<<< orphan*/  lock; int /*<<< orphan*/  ida; int /*<<< orphan*/  thermal_instances; } ;
struct thermal_governor {int dummy; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct thermal_zone_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int THERMAL_MAX_TRIPS ; 
 scalar_t__ THERMAL_NAME_LENGTH ; 
 struct thermal_governor* __find_governor (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bind_tz (struct thermal_zone_device*) ; 
 struct thermal_governor* def_governor ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct thermal_zone_device*) ; 
 struct thermal_zone_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ stub1 (struct thermal_zone_device*,int,int*) ; 
 scalar_t__ stub2 (struct thermal_zone_device*,int,int*) ; 
 int thermal_add_hwmon_sysfs (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  thermal_class ; 
 int /*<<< orphan*/  thermal_governor_lock ; 
 int /*<<< orphan*/  thermal_list_lock ; 
 int thermal_set_governor (struct thermal_zone_device*,struct thermal_governor*) ; 
 int /*<<< orphan*/  thermal_tz_ida ; 
 int /*<<< orphan*/  thermal_tz_list ; 
 int thermal_zone_create_device_groups (struct thermal_zone_device*,int) ; 
 int /*<<< orphan*/  thermal_zone_device_check ; 
 int /*<<< orphan*/  thermal_zone_device_reset (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  thermal_zone_device_update (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 

struct thermal_zone_device *
thermal_zone_device_register(const char *type, int trips, int mask,
			     void *devdata, struct thermal_zone_device_ops *ops,
			     struct thermal_zone_params *tzp, int passive_delay,
			     int polling_delay)
{
	struct thermal_zone_device *tz;
	enum thermal_trip_type trip_type;
	int trip_temp;
	int id;
	int result;
	int count;
	struct thermal_governor *governor;

	if (!type || strlen(type) == 0) {
		pr_err("Error: No thermal zone type defined\n");
		return ERR_PTR(-EINVAL);
	}

	if (type && strlen(type) >= THERMAL_NAME_LENGTH) {
		pr_err("Error: Thermal zone name (%s) too long, should be under %d chars\n",
		       type, THERMAL_NAME_LENGTH);
		return ERR_PTR(-EINVAL);
	}

	if (trips > THERMAL_MAX_TRIPS || trips < 0 || mask >> trips) {
		pr_err("Error: Incorrect number of thermal trips\n");
		return ERR_PTR(-EINVAL);
	}

	if (!ops) {
		pr_err("Error: Thermal zone device ops not defined\n");
		return ERR_PTR(-EINVAL);
	}

	if (trips > 0 && (!ops->get_trip_type || !ops->get_trip_temp))
		return ERR_PTR(-EINVAL);

	tz = kzalloc(sizeof(*tz), GFP_KERNEL);
	if (!tz)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&tz->thermal_instances);
	ida_init(&tz->ida);
	mutex_init(&tz->lock);
	id = ida_simple_get(&thermal_tz_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		result = id;
		goto free_tz;
	}

	tz->id = id;
	strlcpy(tz->type, type, sizeof(tz->type));
	tz->ops = ops;
	tz->tzp = tzp;
	tz->device.class = &thermal_class;
	tz->devdata = devdata;
	tz->trips = trips;
	tz->passive_delay = passive_delay;
	tz->polling_delay = polling_delay;

	/* sys I/F */
	/* Add nodes that are always present via .groups */
	result = thermal_zone_create_device_groups(tz, mask);
	if (result)
		goto remove_id;

	/* A new thermal zone needs to be updated anyway. */
	atomic_set(&tz->need_update, 1);

	dev_set_name(&tz->device, "thermal_zone%d", tz->id);
	result = device_register(&tz->device);
	if (result)
		goto release_device;

	for (count = 0; count < trips; count++) {
		if (tz->ops->get_trip_type(tz, count, &trip_type))
			set_bit(count, &tz->trips_disabled);
		if (tz->ops->get_trip_temp(tz, count, &trip_temp))
			set_bit(count, &tz->trips_disabled);
		/* Check for bogus trip points */
		if (trip_temp == 0)
			set_bit(count, &tz->trips_disabled);
	}

	/* Update 'this' zone's governor information */
	mutex_lock(&thermal_governor_lock);

	if (tz->tzp)
		governor = __find_governor(tz->tzp->governor_name);
	else
		governor = def_governor;

	result = thermal_set_governor(tz, governor);
	if (result) {
		mutex_unlock(&thermal_governor_lock);
		goto unregister;
	}

	mutex_unlock(&thermal_governor_lock);

	if (!tz->tzp || !tz->tzp->no_hwmon) {
		result = thermal_add_hwmon_sysfs(tz);
		if (result)
			goto unregister;
	}

	mutex_lock(&thermal_list_lock);
	list_add_tail(&tz->node, &thermal_tz_list);
	mutex_unlock(&thermal_list_lock);

	/* Bind cooling devices for this zone */
	bind_tz(tz);

	INIT_DELAYED_WORK(&tz->poll_queue, thermal_zone_device_check);

	thermal_zone_device_reset(tz);
	/* Update the new thermal zone and mark it as already updated. */
	if (atomic_cmpxchg(&tz->need_update, 1, 0))
		thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);

	return tz;

unregister:
	device_del(&tz->device);
release_device:
	put_device(&tz->device);
	tz = NULL;
remove_id:
	ida_simple_remove(&thermal_tz_ida, id);
free_tz:
	kfree(tz);
	return ERR_PTR(result);
}